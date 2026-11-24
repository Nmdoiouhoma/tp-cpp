export module lzw.encoderv2;
import std;
import lzw.encoder;

export namespace lzw {

    // Version 2 : le dictionnaire est std::map (arbre rouge-noir équilibré).
    class EncoderV2 : public Encoder {
    public:
        void Encode(std::ifstream& in, std::ofstream& out) override {
            std::map<std::string, CodeType> dictionary;
            std::size_t nextCode{256};
            for (std::size_t byte = 0; byte < 256; ++byte) {
                dictionary[std::string(1, static_cast<char>(byte))] = static_cast<CodeType>(byte);
            }

            std::string s;
            char c{};
            while (in.get(c)) {
                s += c;
                if (!dictionary.contains(s)) {
                    if (nextCode < MaxDictionarySize) {
                        dictionary[s] = static_cast<CodeType>(nextCode);
                        ++nextCode;
                    }
                    s.pop_back();
                    WriteCode(out, dictionary.at(s));
                    s = std::string(1, c);
                }
            }
            if (!s.empty()) {
                WriteCode(out, dictionary.at(s));
            }
        }

        void Decode(std::ifstream& in, std::ofstream& out) override {
            std::map<CodeType, std::string> dictionary;
            std::size_t nextCode{256};
            for (std::size_t byte = 0; byte < 256; ++byte) {
                dictionary[static_cast<CodeType>(byte)] = std::string(1, static_cast<char>(byte));
            }

            std::string s;
            CodeType k{};
            while (ReadCode(in, k)) {
                if (k > nextCode) {
                    throw std::runtime_error("Cannot decode: invalid code");
                }
                if (k == nextCode) {
                    if (s.empty()) {
                        throw std::runtime_error("Cannot decode: invalid code");
                    }
                    dictionary[static_cast<CodeType>(nextCode)] = s + s[0];
                    ++nextCode;
                } else if (!s.empty() && nextCode < MaxDictionarySize) {
                    dictionary[static_cast<CodeType>(nextCode)] = s + dictionary.at(k)[0];
                    ++nextCode;
                }
                const std::string& entry = dictionary.at(k);
                out.write(entry.data(), static_cast<std::streamsize>(entry.size()));
                s = entry;
            }
        }
    };

}
