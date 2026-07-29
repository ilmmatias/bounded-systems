#include "spectral_profile.hxx"
#include "wl_profile.hxx"

#include <charconv>
#include <filesystem>
#include <format>
#include <print>
#include <span>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace {

struct OutputArguments {
    int vertexCount;
    std::filesystem::path outputDirectory;
};

int parseInteger(std::string_view text, std::string_view opt) {
    int value = 0;
    const auto [end, error] =
        std::from_chars(text.data(), text.data() + text.size(), value);

    if (error != std::errc{} || end != text.data() + text.size()) {
        throw std::invalid_argument(
            std::format("{} requires an integer", opt));
    }

    return value;
}

OutputArguments parseOutputArguments(std::span<char*> args) {
    int vertexCount = 0;
    std::filesystem::path outputDirectory;

    for (size_t index = 0; index < args.size(); ++index) {
        const std::string_view opt = args[index];

        if (opt == "--vertices") {
            if (++index == args.size()) {
                throw std::invalid_argument("--vertices requires a value");
            }

            vertexCount = parseInteger(args[index], opt);
            continue;
        }

        if (opt == "--output") {
            if (++index == args.size()) {
                throw std::invalid_argument("--output requires a value");
            }

            outputDirectory = args[index];
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
        const auto options = args.subspan(2);

        if (command == "spectral") {
            const auto parsed = parseOutputArguments(options);
            return generateSpectralArtifacts(parsed.vertexCount,
                                             parsed.outputDirectory);
        }

        if (command == "wl-scan") {
            if (!options.empty()) {
                throw std::invalid_argument("wl-scan takes no options");
            }

            return generateWlScan();
        }

        if (command == "wl-reduce") {
            const auto parsed = parseOutputArguments(options);
            return generateWlReduction(parsed.vertexCount,
                                       parsed.outputDirectory);
        }

        printUsage(args.front());
        return 1;
    } catch (const std::exception& error) {
        std::println(stderr, "fatal: {}", error.what());
        return 2;
    }
}
