const width = process.argv[2];
process.argv.slice(3).forEach(img =>
    require('get-pixels')(img + '.png', (err, pxs) => {
        if (err) return console.log(err);
        if (pxs.shape[1] !== 64 || pxs.shape[0] !== width * 32) return console.log('Incorrect dimensions');
        const arr = Array.from(pxs.data).map(x => Math.round(x * 7 / 255)).filter((x, i) => i % 4 !== 3), panels = new Array(width).fill([]);
        while (arr.length) panels.forEach(x => x.push(arr.splice(0, 96)));
        panels.forEach((x, i) => require('fs').writeFileSync(`${img}${i}.h`, `const byte ${img}[64][32][3] PROGMEM={${x.join(",")}};`));
    })
);