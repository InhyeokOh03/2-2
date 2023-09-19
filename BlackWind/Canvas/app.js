const canvas = document.getElementById("my_canvas");
const ctx = canvas.getContext("2d");

canvas.width = 1000;
canvas.height = 1000;

// let x = 10;
// let y = 10;

// let rectangle_width = 100;
// let rectangle_height = 100;

// // 문자열을 사용하여서 색 넣기
// ctx.fillStyle = "rgb(200, 0, 0)";
// ctx.fillRect(x, y, rectangle_width, rectangle_height);

// x = x + 100;
// y = y + 100;


// ctx.fillStyle = "rgba(0, 0, 200, 0.5)";
// ctx.fillRect(x, y, rectangle_width, rectangle_height);

let my_rectangle = {
    x: 10,
    y: 10,
    width: 100,
    height: 100,
};

ctx.fillStyle = "rgb(200, 0, 0)";
ctx.fillRect(my_rectangle.x, my_rectangle.y, my_rectangle.width, my_rectangle.height);
// top triangle
ctx.beginPath();
ctx.moveTo(10, 10);
ctx.lineTo(50, 10);
ctx.lineTo(10, 50);
ctx.fillStyle = "rgb(255, 255, 255)";
ctx.fill();
// bottom triangle
ctx.beginPath();
ctx.moveTo(110, 110);
ctx.lineTo(70, 110);
ctx.lineTo(110, 70);
ctx.fill();