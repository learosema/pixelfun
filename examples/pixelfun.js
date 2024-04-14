/**
 * Cosine based palette, 4 vec3 params
 * @see https://iquilezles.org/articles/palettes/
 * @param {float} t a parameter between 0..1 (can be bigger, lower but repeats)
 * @param {[number, number, number]} a first vector
 * @param {[number, number, number]} b second vector
 * @param {[number, number, number]} c third vector
 * @param {[number, number, number]} d fourth vector
 * @returns {[number, number, number]} an RGB value
 */
function palette(t, a, b, c, d)
{
	const twoPI = 2 * Math.PI;
	return [
		a[0] + b[0] * Math.cos(twoPI * (c[0] * t + d[0])),
		a[1] + b[1] * Math.cos(twoPI * (c[1] * t + d[1])),
		a[2] + b[2] * Math.cos(twoPI * (c[2] * t + d[2]))
	].map(val => Math.round(val*255));
}

function twilight(t) {
	return palette(t,
		[0.5, 0.5, 0.5],
		[0.5, 0.5, 0.5],
		[2.0, 1.0, 0.0],
		[0.5, 0.2, 0.25]
	);
}

function pixelfun(x, y, t) {
	const { sin, cos } = Math;
	const i = 0.5+0.5*sin(x*0.5 + t);
	const j = 0.5+0.5*cos(y*0.5 + t);

	return twilight(t * 0.2 + i*j);
}
