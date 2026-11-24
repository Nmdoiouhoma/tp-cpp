export module lzw.encoderv1;
import std;
import exo9;
import lzw.encoder;

export namespace lzw {

    // Version 1 : le dictionnaire est la classe Map de l'exercice 9 (arbre binaire non équilibré).
    class EncoderV1 : public Encoder {
    public:
        void Encode(std::ifstream& in, std::ofstream& out) override {
            exo9::Map<std::string, CodeType> dictionary;
            std::size_t nextCode{256};
            for (std::size_t byte = 0; byte < 256; ++byte) {
                dictionary.Put(std::string(1, static_cast<char>(byte)), static_cast<CodeType>(byte));
            }

            std::string s;
            char c{};
            while (in.get(c)) {
                s += c;
                if (!dictionary.Find(s).has_value()) {
                    if (nextCode < MaxDictionarySize) {
                        dictionary.Put(s, static_cast<CodeType>(nextCode));
                        ++nextCode;
                    }
                    s.pop_back();
                    WriteCode(out, dictionary.Get(s));
                    s = std::string(1, c);
                }
            }
            if (!s.empty()) {
                WriteCode(out, dictionary.Get(s));
            }
        }

        void Decode(std::ifstream& in, std::ofstream& out) override {
            exo9::Map<CodeType, std::string> dictionary;
            std::size_t nextCode{256};
            for (std::size_t byte = 0; byte < 256; ++byte) {
                dictionary.Put(static_cast<CodeType>(byte), std::string(1, static_cast<char>(byte)));
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
                    dictionary.Put(static_cast<CodeType>(nextCode), s + s[0]);
                    ++nextCode;
                } else if (!s.empty() && nextCode < MaxDictionarySize) {
                    dictionary.Put(static_cast<CodeType>(nextCode), s + dictionary.Get(k)[0]);
                    ++nextCode;
                }
                const std::string& entry = dictionary.Get(k);
                out.write(entry.data(), static_cast<std::streamsize>(entry.size()));
                s = entry;
            }
        }
    };

}
