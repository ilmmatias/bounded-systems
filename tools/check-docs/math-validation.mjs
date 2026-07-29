import katex from "katex";
import { init as initMathJax } from "mathjax";

export function checkKatexTypesetting(documents, diagnostics) {
  for (const document of documents.values()) {
    for (const expression of document.math) {
      try {
        katex.renderToString(expression.tex, {
          displayMode: expression.display,
          throwOnError: true,
          strict: "error",
        });
      } catch (error) {
        diagnostics.add(
          document.file,
          "katex",
          `repair TeX expression: ${error.message}`,
          expression.line,
        );
      }
    }
  }
}

async function createMathJax() {
  return initMathJax({
    loader: { load: ["input/tex", "output/svg"] },
    tex: { packages: ["base", "ams", "newcommand"] },
    startup: { typeset: false },
  });
}

function hasMathJaxError(renderedExpression) {
  return /<(?:merror|mjx-merror)\b|data-mjx-error/i.test(renderedExpression);
}

async function typesetWithWarnings(MathJax, expression) {
  const warnings = [];
  const originalWarn = console.warn;

  console.warn = (...parts) => warnings.push(parts.join(" "));

  try {
    const node = await MathJax.tex2svgPromise(expression.tex, {
      display: expression.display,
    });

    const renderedExpression = MathJax.startup.adaptor.outerHTML(node);

    return { renderedExpression, warnings };
  } finally {
    console.warn = originalWarn;
  }
}

export async function checkMathJaxTypesetting(documents, diagnostics) {
  const MathJax = await createMathJax();

  for (const document of documents.values()) {
    for (const expression of document.math) {
      try {
        const { renderedExpression, warnings } = await typesetWithWarnings(
          MathJax,
          expression,
        );

        if (hasMathJaxError(renderedExpression)) {
          diagnostics.add(
            document.file,
            "mathjax",
            "repair TeX expression rejected during strict typesetting",
            expression.line,
          );
        }

        for (const warning of warnings) {
          diagnostics.add(
            document.file,
            "mathjax",
            `resolve typesetting warning: ${warning}`,
            expression.line,
          );
        }
      } catch (error) {
        diagnostics.add(
          document.file,
          "mathjax",
          `repair TeX expression: ${error.message}`,
          expression.line,
        );
      }
    }
  }
}
