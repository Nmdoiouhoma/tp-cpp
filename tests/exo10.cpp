#include <catch2/catch_all.hpp>
import std;
import lzw;
import lzw.encoder;
import lzw.encoderv1;
import lzw.encoderv2;
import lzw.encoderv3;

namespace {

    std::string ReadFile(const std::filesystem::path& path) {
        std::ifstream in(path, std::ios::binary);
        return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
    }

    // Compresse puis décompresse `content` avec l'encodeur EncoderT ; retourne {taille compressée, contenu relu}.
    template <typename EncoderT>
    std::pair<std::size_t, std::string> RoundTrip(const std::string& content) {
        const auto dir = std::filesystem::temp_directory_path();
        const auto source = dir / "lzw_test_source.bin";
        const auto compressed = dir / "lzw_test_compressed.bin";
        const auto decompressed = dir / "lzw_test_decompressed.bin";
        {
            std::ofstream out(source, std::ios::binary);
            out << content;
        }
        EncoderT encoder;
        {
            std::ifstream in(source, std::ios::binary);
            std::ofstream out(compressed, std::ios::binary);
            encoder.Encode(in, out);
        }
        {
            std::ifstream in(compressed, std::ios::binary);
            std::ofstream out(decompressed, std::ios::binary);
            encoder.Decode(in, out);
        }
        return {std::filesystem::file_size(compressed), ReadFile(decompressed)};
    }

}

TEMPLATE_TEST_CASE("Exo10 LZW aller-retour", "", lzw::EncoderV1, lzw::EncoderV2, lzw::EncoderV3) {
    SECTION("Fichier vide") {
        const auto [size, back] = RoundTrip<TestType>("");
        REQUIRE(size == 0);
        REQUIRE(back.empty());
    }
    SECTION("Un seul octet") {
        const auto [size, back] = RoundTrip<TestType>("A");
        REQUIRE(size == 2);
        REQUIRE(back == "A");
    }
    SECTION("Exemple classique de Wikipédia") {
        const std::string text = "TOBEORNOTTOBEORTOBEORNOT";
        const auto [size, back] = RoundTrip<TestType>(text);
        REQUIRE(back == text);
    }
    SECTION("Cas particulier du décodeur (code pas encore dans le dictionnaire)") {
        const std::string text(1000, 'a');
        const auto [size, back] = RoundTrip<TestType>(text);
        REQUIRE(back == text);
        REQUIRE(size < text.size() / 10);
    }
    SECTION("Texte répétitif compressé") {
        std::string text;
        for (int i = 0; i < 200; ++i) {
            text += "Le C++ moderne, c'est bien. ";
        }
        const auto [size, back] = RoundTrip<TestType>(text);
        REQUIRE(back == text);
        REQUIRE(size < text.size());
    }
    SECTION("Tous les octets, y compris ceux au-dessus de 127") {
        std::string text;
        for (int i = 0; i < 1024; ++i) {
            text.push_back(static_cast<char>(i % 256));
        }
        const auto [size, back] = RoundTrip<TestType>(text);
        REQUIRE(back == text);
    }
}

TEMPLATE_TEST_CASE("Exo10 LZW dictionnaire plein", "", lzw::EncoderV2, lzw::EncoderV3) {
    std::mt19937 generator(42);
    std::string text;
    for (int i = 0; i < 400000; ++i) {
        text.push_back(static_cast<char>(generator() % 256));
    }
    const auto [size, back] = RoundTrip<TestType>(text);
    REQUIRE(back == text);
}

TEST_CASE("Exo10 LZW code invalide") {
    const auto dir = std::filesystem::temp_directory_path();
    const auto compressed = dir / "lzw_test_invalid.bin";
    const auto decompressed = dir / "lzw_test_invalid_out.bin";
    {
        std::ofstream out(compressed, std::ios::binary);
        lzw::WriteCode(out, 65);
        lzw::WriteCode(out, 9999);
    }
    lzw::EncoderV3 encoder;
    std::ifstream in(compressed, std::ios::binary);
    std::ofstream out(decompressed, std::ios::binary);
    REQUIRE_THROWS_AS(encoder.Decode(in, out), std::runtime_error);
}

TEST_CASE("Exo10 Application") {
    const auto dir = std::filesystem::temp_directory_path();
    const auto source = dir / "lzw_app_source.txt";
    {
        std::ofstream out(source, std::ios::binary);
        for (int i = 0; i < 100; ++i) {
            out << "Le C++ moderne, c'est bien. ";
        }
    }
    const auto compressed = dir / "lzw_app_compressed.bin";
    const auto decompressed = dir / "lzw_app_decompressed.txt";
    const lzw::Application application{source.string(), compressed.string(), decompressed.string()};
    REQUIRE(ReadFile(decompressed) == ReadFile(source));
    REQUIRE(std::filesystem::file_size(compressed) < std::filesystem::file_size(source));
}
