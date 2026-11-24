export module lzw.application;
import std;
import lzw.encoder;
import lzw.encoderv1;
import lzw.encoderv2;
import lzw.encoderv3;

export namespace lzw {

    class Application {
    public:
        Application(const std::string& source, const std::string& compressed, const std::string& decompressed) {
            EncoderV1 v1;
            EncoderV2 v2;
            EncoderV3 v3;
            for (Encoder* encoder : std::initializer_list<Encoder*>{&v1, &v2, &v3}) {
                Run(*encoder, source, compressed, decompressed);
            }
        }

    private:
        static void Run(Encoder& encoder, const std::string& source,
                        const std::string& compressed, const std::string& decompressed) {
            // Compression
            const auto compressStart = std::chrono::high_resolution_clock::now();
            {
                std::ifstream in(source, std::ios::binary);
                if (!in) {
                    throw std::runtime_error("Cannot open " + source);
                }
                std::ofstream out(compressed, std::ios::binary);
                encoder.Encode(in, out);
            }
            const auto compressEnd = std::chrono::high_resolution_clock::now();
            const auto compressMs = std::chrono::duration<double, std::milli>(compressEnd - compressStart).count();

            const auto uncompressedSize = std::filesystem::file_size(source);
            const auto compressedSize = std::filesystem::file_size(compressed);
            const double ratio = uncompressedSize == 0
                ? 0.0
                : 100.0 * static_cast<double>(compressedSize) / static_cast<double>(uncompressedSize);
            std::cout << uncompressedSize << " bytes uncompressed, " << compressedSize
                      << " bytes compressed, " << ratio << "% in " << compressMs << "ms\n";

            // Décompression
            const auto decompressStart = std::chrono::high_resolution_clock::now();
            {
                std::ifstream in(compressed, std::ios::binary);
                std::ofstream out(decompressed, std::ios::binary);
                encoder.Decode(in, out);
            }
            const auto decompressEnd = std::chrono::high_resolution_clock::now();
            const auto decompressMs = std::chrono::duration<double, std::milli>(decompressEnd - decompressStart).count();
            std::cout << "uncompress in " << decompressMs << "ms\n";
        }
    };

}
