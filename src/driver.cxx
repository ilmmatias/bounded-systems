#include "spectral_profile.hxx"
#include "wl_profile.hxx"

#include <charconv>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <format>
#include <print>
#include <span>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <utility>

namespace {

struct OutputOptions {
    int vertexCount;
    std::filesystem::path outputDirectory;
};

int parseInt(std::string_view text, std::string_view opt) {
    int value = 0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(std::format("{} requires an integer", opt));
    }

    return value;
}

OutputOptions parseOutputOptions(std::span<char*> args) {
    int vertexCount = 0;
    std::filesystem::path outputDirectory;

    for (size_t i = 0; i < args.size(); ++i) {
        const std::string_view opt = args[i];

        if (opt == "--vertices") {
            if (++i == args.size()) {
                throw std::invalid_argument("--vertices requires a value");
            }

            vertexCount = parseInt(args[i], opt);
            continue;
        }

        if (opt == "--output") {
            if (++i == args.size()) {
                throw std::invalid_argument("--output requires a value");
            }

            outputDirectory = args[i];
            continue;
        }

        throw std::invalid_argument(std::format("unknown option: {}", opt));
    }

    if (vertexCount == 0) {
        throw std::invalid_argument("missing --vertices");
    }

    if (outputDirectory.empty()) {
        throw std::invalid_argument("missing --output");
    }

    return {
        .vertexCount = vertexCount,
        .outputDirectory = std::move(outputDirectory),
    };
}

void printUsage(std::string_view program) {
    std::print(stderr,
               "usage:\n"
               "  {} spectral --vertices N --output DIRECTORY\n"
               "  {} wl-scan\n"
               "  {} wl-reduce --vertices N --output DIRECTORY\n",
               program, program, program);
}

} // namespace

int main(int argc, char** argv) {
    try {
        const std::span args(argv, static_cast<size_t>(argc));

        if (args.size() < 2) {
            printUsage(args.front());
            return 1;
        }

        const std::string_view command = args[1];
        const auto optArgs = args.subspan(2);

        if (command == "spectral") {
            const OutputOptions opt = parseOutputOptions(optArgs);
            return generateSpectralArtifacts(opt.vertexCount,
                                             opt.outputDirectory);
        }

        if (command == "wl-scan") {
            if (!optArgs.empty()) {
                throw std::invalid_argument("wl-scan takes no options");
            }

            return generateWlScan();
        }

        if (command == "wl-reduce") {
            const OutputOptions opt = parseOutputOptions(optArgs);
            return generateWlReduction(opt.vertexCount, opt.outputDirectory);
        }

        printUsage(args.front());
        return 1;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        return 2;
    }
}
