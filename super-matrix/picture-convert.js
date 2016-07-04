process.argv.slice(2).forEach(img =>
    require('get-pixels')(img + '.png', (err, pxs) => {
        if (err) return console.log(err);
        if (pxs.shape[1] !== 64 || pxs.shape[0] !== 96) return console.log('Dimensions must be 64 x 96');
        const arr = Array.from(pxs.data).map(x => Math.round(x * 7 / 255)).filter((x, i) => i % 4 !== 3), panels = [[], [], []];
        while (arr.length) panels.forEach(x => x.push(arr.splice(0, 96)));
        panels.forEach((x, i) => require('fs').writeFileSync(`${img}${i}.h`, `const byte ${img}[64][32][3] PROGMEM={${x.join(",")}};`));
    })
);