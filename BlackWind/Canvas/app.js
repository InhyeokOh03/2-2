//app.js
console.log("start");

const canvas = document.getElementById("my_canvas");
const ctx = canvas.getContext("2d");

let screen = {
    width: 500,
    height: 500,
};

canvas.width = screen.width;
canvas.height = screen.height;

let ball = {
    x: 100,
    y: 100,
    r: 20,
};

function move_ball(screen, ball, dx, dy) {
    ball.x += dx;
    ball.y += dy;
		
    if ( ball.x + ball.r > screen.width) {
        ball.x = screen.width - ball.r;
    }
    else if ( ball.x - ball.r < 0) {
        ball.x = ball.r;
    }
    else if (ball.y + ball.r > screen.height) {
        ball.y = screen.height - ball.r;
    }
    else if (ball.y - ball.r < 0) {
        ball.y = ball.r;
    }

    return ball;
}

function draw() {
    ctx.clearRect(0, 0, screen.width, screen.height);
    ctx.beginPath();
    ctx.arc(ball.x, ball.y, ball.r, 0, Math.PI*2);
    ctx.fillStyle = "#0095DD";
    ctx.fill();
    ctx.closePath();
    move_ball(screen, ball, 0, -10)
}

setInterval(draw, 50);