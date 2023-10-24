class Ball {
    constructor(x, y, r) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.speed = {
            dx: 0,
            dy: 0,
        };
    }
    set_speed(dx, dy) {
        this.speed.dx = dx;
        this.speed.dy = dy;
    }
    animate() {
        window.requestAnimationFrame(this.animate.bind(this));
        this.ctx.clearRect(0, 0, this.stageWidth, this.stageHeight);
    
        this.ball.update(); // Ball 클래스의 update 메서드 호출로 위치 업데이트
        this.ball.draw(this.ctx); // Ball 클래스의 draw 메서드 호출로 공 그리기
    }
    draw(ctx) {
        ctx.beginPath();
        ctx.arc(this.x, this.y, this.r, 0, Math.PI*2);
        ctx.fillStyle = "#0095DD";
        ctx.fill();
        ctx.closePath();
        this.update();
    }
    update() {
        this.x += this.speed.dx;
        this.y += this.speed.dy;

        // 화면 경계에 부딪히면 속력을 반대로 바꿉니다.
        if (this.x - this.r < 0 || this.x + this.r > this.stageWidth) {
            this.speed.dx = -this.speed.dx;
        }
        if (this.y - this.r < 0 || this.y + this.r > this.stageHeight) {
            this.speed.dy = -this.speed.dy;
        }
    }
}

class App {
    constructor() {
        this.canvas = document.createElement('canvas');
        document.body.appendChild(this.canvas);
        this.ctx = this.canvas.getContext('2d');
				
				// 이부분은 canvas 높이 너비 세팅하는거임
        this.stageWidth = document.body.clientWidth;
        this.stageHeight = document.body.clientHeight;
        this.canvas.width = this.stageWidth;
        this.canvas.height = this.stageHeight
        this.canvas.style.width = this.stageWidth + "px";
        this.canvas.style.height = this.stageHeight + "px";

        this.make_ball();
        window.requestAnimationFrame(this.animate.bind(this));
    }
    make_ball() {
        this.ball = new Ball(10, 10, 10);
        this.ball.set_speed(10, 10);
    }
    animate() {
        window.requestAnimationFrame(this.animate.bind(this));
        this.ctx.clearRect(0, 0, this.stageWidth, this.stageHeight);
    
        this.ball.draw(this.ctx);
    }
}



window.onload = () => {
    new App();

}