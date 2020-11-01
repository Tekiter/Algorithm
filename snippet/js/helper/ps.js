"use strict";

const ps = (function (process) {
  const readline = require("readline");

  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });

  let lines = [];
  let cursor = 0;

  rl.on("line", function (line) {
    lines.push(line);
  });

  return {
    main(f) {
      f()
        .catch((err) => {
          throw err;
        })
        .finally(() => {
          rl.close();
        });
    },
    readLine: async function readLine() {
      return new Promise((resolve) => {
        if (cursor < lines.length) {
          resolve(lines[cursor++]);
        } else {
          setTimeout(
            () =>
              readLine().then((line) => {
                resolve(line);
              })
          );
        }
      });
    },
    async readLineAsArray() {
      const line = await this.readLine()
      return line.split(/\s/).map(t=>parseInt(t))
    },
    write(data) {
      process.stdout.write(data + "");
    },
    writeLine(data) {
      process.stdout.write(data + "\n");
    },
  };
})(process);


ps.main(async () => {
  /* main logic goes here */

  let line = await ps.readLine()
  ps.writeLine('input: ' + line)
});
