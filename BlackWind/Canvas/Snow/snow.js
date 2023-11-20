const PI2 = Math.PI * 2;

export class SnowParticle {
    constructor(x, y, radius, rgb) {
        this.x = x;
        this.y = y;
        this.radius = radius;
        this.vy = Math.random() * 4;
        
        this.sinValue = Math.random();
    }

    animate(ctx, stageWidth, stageHeight) {
        this.y += this.vy;

        this.vx = 0.5
        this.x += this.vx;

        if (this.y > stageHeight + 10) {
            this.y = -10;
        }
        if (this.x > stageWidth + 10) {
            this.x = -10
        }

        ctx.beginPath();

        ctx.arc(this.x, this.y, this.radius, 0, PI2, false);
        ctx.fill();
    }
}