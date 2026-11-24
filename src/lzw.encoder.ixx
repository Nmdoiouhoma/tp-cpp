export module lzw.encoder;
import std;

export namespace lzw {

    // Un code est un nombre de 16 bits : il peut désigner jusqu'à 65536 entrées du dictionnaire.
    using CodeType = std::uint16_t;
    constexpr std::size_t MaxDictionarySize = std::numeric_limits<CodeType>::max() + 1;

    // Interface commune à toutes les versions de l'encodeur (Map maison, std::map, std::unordered_map).
    class Encoder {
    public:
        virtual ~Encoder() = default;
        virtual void Encode(std::ifstream& in, std::ofstream& out) = 0;
        virtual void Decode(std::ifstream& in, std::ofstream& out) = 0;
    };

    // Écrit un code (2 octets) dans le fichier compressé.
    void WriteCode(std::ofstream& out, const CodeType code) {
        out.write(reinterpret_cast<const char*>(&code), sizeof(code));
    }

    // Lit un code (2 octets) dans le fichier compressé ; false quand il n'y en a plus.
    bool ReadCode(std::ifstream& in, CodeType& code) {
        return static_cast<bool>(in.read(reinterpret_cast<char*>(&code), sizeof(code)));
    }

}
