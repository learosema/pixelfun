function pixelfun(x, y, t) {
  return [
	(x * 255 / WIDTH),
	(y * 255 / HEIGHT), 128 + 127*Math.sin(x*0.01 + t*0.1)];
}
