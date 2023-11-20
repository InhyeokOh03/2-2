import { GlowParticle } from "./glowparticles.js";
import { SnowParticle } from "./snow.js";

const COLORS = [
    {r: 45, g: 74, b: 227}, // blue
    {r: 250, g: 255, b: 89},// yellow
    {r: 255, g: 104, b: 248}, // pupple
    {r: 44, g: 209, b: 252}, // skyblue
    {r: 54, g: 233, b: 84}, // green
    {r: 255, g: 255, b: 255} // white
];

// let frame = 0;

class Block {
    constructor(width, height, x, y) {
        this.width = width;
        this.height = height;
        this.x = x;
        this.y = y;
        this.maxX = width + x;
        this.maxY = height + y;
    }
    
    draw(ctx) {
        const xGap = 80;
        const yGap = 60;

        ctx.fillStyle = '#ffffff';
        ctx.beginPath();
        ctx.rect(this.x, this.y, this.width, this.height);
        ctx.fill();
    }
}
class App {
    constructor(){
        this.canvas = document.createElement('canvas');
        document.body.appendChild(this.canvas);
        this.ctx = this.canvas.getContext('2d');

        this.pixelRatio = (window.devicePixelRatio > 1) ? 2 : 1;

        this.totalParticles = 150;
        this.particles = [];
        this.maxRadius = 900;
        this.minRadius = 400;

        window.addEventListener('resize', this.resize.bind(this), false);
        this.resize();
        this.block = new Block(this.stageWidth, 50, 0, this.stageHeight / 2);
        this.block2 = new Block(50, this.stageHeight, this.stageWidth / 2, 0);

        this.block3 = new Block(this.stageWidth, 25, 0, 0);
        this.block4 = new Block(25, this.stageHeight, 0, 0);
        this.block5 = new Block(-this.stageWidth, -25, this.stageWidth, this.stageHeight);
        this.block6 = new Block(-25, -this.stageHeight, this.stageWidth, this.stageHeight);

        window.requestAnimationFrame(this.animate.bind(this));
    }

    resize() {
        this.stageWidth = document.body.clientWidth;
        this.stageHeight = document.body.clientHeight;

        this.canvas.width = this.stageWidth * this.pixelRatio;
        this.canvas.height = this.stageHeight * this.pixelRatio;
        this.ctx.scale(this.pixelRatio, this.pixelRatio);

        this.ctx.globalCompositeOperation = 'saturation';

        // this.createParticles();
        this.createSnow();
    }

    createParticles() {
        let curColor = 0;
        this.particles = [];

        for (let i = 0; i < this.totalParticles; i++) {
            const item = new GlowParticle(
                Math.random() * this.stageWidth,
                Math.random() * this.stageHeight,
                Math.random() *
                (this.maxRadius - this.minRadius) +this.minRadius,
                COLORS[curColor]
            );

            if (++curColor >= COLORS.length) {
                curColor = 0;
            }

            this.particles[i] = item;
        }
    }

    createSnow() {
        this.particles = [];

        for (let i = 0; i < this.totalParticles; i++) {
            const item = new SnowParticle(
                Math.random() * this.stageWidth,
                -100,
                10,
                COLORS[5]
            );

            this.particles[i] = item;
        }
    }

    animate() {
        window.requestAnimationFrame(this.animate.bind(this));

        this.ctx.clearRect(0, 0, this.stageWidth, this.stageHeight);

        for (let i = 0; i < this.totalParticles; i++) {
            const item = this.particles[i];
            item.animate(this.ctx, this.stageWidth, this.stageHeight);
        }
        this.block.draw(this.ctx);
        this.block2.draw(this.ctx);
        this.block3.draw(this.ctx);
        this.block4.draw(this.ctx);
        this.block5.draw(this.ctx);
        this.block6.draw(this.ctx);

    }
}


window.onload = () => {
    new App();
}

