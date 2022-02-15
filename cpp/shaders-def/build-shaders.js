const fs = require('fs'),
    readline = require('readline'),
    def = require('./shaders-def.json'),
    outFileName = '../src/include/shaders-def.h';

fs.writeFileSync(outFileName, "", { flag: 'w+' });
Object.keys(def).forEach(process_json);

async function process_json(shader_name) {
    let s = await processLineByLine(shader_name, def[shader_name]);

    console.info("WRITING SHADER ", shader_name);
    fs.writeFileSync(outFileName, s, { flag: 'a' });
}

async function processLineByLine(shader_name, fname) {
    const fileStream = fs.createReadStream('./src/'+fname);
    let s = '#define ' + shader_name + ' "';

    const rl = readline.createInterface({
        input: fileStream,
        crlfDelay: Infinity
    });
    // Note: we use the crlfDelay option to recognize all instances of CR LF
    // ('\r\n') in input.txt as a single line break.

    for await (const line of rl) {
        // Each line in input.txt will be successively available here as `line`.
        if (line !== "" && line.trim().indexOf("//") !== 0) {
            let cont = line.trim(),
                line_cont = cont.indexOf('#define') === 0 ? "\\n"+cont+"\\n" : (
                    cont.indexOf("#version 300 es") === 0 ? cont+"\\n" :
                    cont
                );

            s += line_cont + " ";
        }
    }
    s += '";\n';

    return s;
}