process.argv.slice(2).forEach(img =>
    require('get-pixels')(img + '.png', (err, pxs) => {
        if (err) return console.log(err);
        if (pxs.shape[1] !== 64 || pxs.shape[0] !== 96) return console.log('Dimensions must be 64 x 96');
        require('fs').writeFileSync(img + '.h', `const byte ${img}[64][96][4] PROGMEM={${Array.from(pxs.data).map(x => Math.round(x * 7 / 255)).join(",")}};`);
    })
);