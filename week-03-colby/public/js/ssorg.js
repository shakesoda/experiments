// site stuff
// http://paulirish.com/2011/requestanimationframe-for-smart-animating/
window.requestAnimFrame = (function() {
	return window.requestAnimationFrame    || 
		window.webkitRequestAnimationFrame ||
		window.mozRequestAnimationFrame    ||
		window.oRequestAnimationFrame      ||
		window.msRequestAnimationFrame     ||
		function(callback, element) {
			window.setTimeout(callback, 1000 / 60)
		}
})()

function addEvents(obj, list, evt) {
	function isArray(value) {
		return (value instanceof Array)
	}
	// sanity
	if (isArray(list) && !evt)
		alert("addEvents takes an Object, not an Array!")

	// bind all the events in the list as needed
	var keys = evt ? list : Object.keys(list)
	for (i in keys) {
		// we are recursing if evt is present.
		var key = evt ? evt : keys[i]
		var fn = evt ? list[i] : list[key]
		
		// call ourselves while passing the key if we've got an array.
		if (isArray(fn)) {
			addEvents(obj, fn, key)
			continue
		}
		if (obj.addEventListener)
			obj.addEventListener(key, fn, false)
		else if (obj.attachEvent)
			obj.attachEvent("on"+key, fn)
	}
}

var ctx
var then = new Date()

// wave settings
var params = {
	offset: 20,
	width: 512,
	speed: 3000,
	rounding: 0,
	power: 15
}

function onResize() {
	$("#wave").css("width", $(window).width())
}

function updateCurve() {
	var now = new Date()
	var p1 = Math.sin(now.getTime() / params.speed) * params.power + params.offset
	var p2 = Math.cos(now.getTime() / params.speed) * params.power + params.offset

	// We don't actually have to clear because it's filled.
	ctx.fillStyle = $("body").css("backgroundColor")
	ctx.fillRect(0, 0, params.width, params.offset*2)

	// Draw wave
	ctx.beginPath()

	ctx.bezierCurveTo(
		0, params.offset+params.rounding, 0,
		params.offset, Math.abs(params.rounding), params.offset
	)
	ctx.bezierCurveTo(
		params.width/3, p1, (params.width/3)*2,
		p2, params.width, params.offset
	)
	ctx.bezierCurveTo(
		params.width-Math.abs(params.rounding), params.offset, params.width,
		params.offset, params.width, params.offset+params.rounding
	)

	ctx.lineTo(params.width, 0)
	ctx.lineTo(0, 0)

	ctx.fillStyle = $("#header").css("backgroundColor")
	ctx.fill()
	ctx.closePath()

	// queue up the next frame
	requestAnimFrame(updateCurve)
}
function init() {
	var canvas = document.getElementById("wave")
	canvas.width = 512
	canvas.height = params.offset*2
	ctx = canvas.getContext("2d")
	updateCurve()

	if (ctx) {
		// Make sure we're the right size in the right spot.
		$("#wave").css("height", '60px')
		$("#wave").css("position", "relative")
		$("#wave").css("top", params.offset/2+'px')
	}

	// Change header color
	$(".color-change").click(function() {
		var title = $(this).attr("title")
		$("#header").css("backgroundColor", title)
		$.cookie("headerColor", title)
		return false
	})

	// Textarea fanciness
	var msg = "Enter a message..."
	$(".post-box textarea").focus(function() {
		if ($(this).val() == msg)
			$(this).val("")
		$(this).stop().animate({
			boxShadow: '0 1px 8px rgba(0, 130, 150, 1)',
			backgroundColor: '#fff',
			color: 'black'
		}, 250)
	})
	$("textarea").blur(function() {
		if ($(this).val() == '' || $(this).val() == msg)
			$(this).val(msg)
		$(this).stop().animate({
			boxShadow: '0 0 0 white',
			backgroundColor: '#dce1e4',
			color: '#555'
		}, 250)
	})

	// Make sure these are set initially.
	$("#header").css("backgroundColor", $.cookie("headerColor"))
	$("textarea").trigger("blur")
	
	$("form").submit(function(e) {
		if ($("textarea").val() == msg) {
			$("#alert").css("backgroundColor", "#fcc")
			$("#alert").stop().slideDown(150).animate({
				backgroundColor: "#b34",
				height: "100%"
			}, 250)
			return false
		}
	})
}

// I really should just patch/extend jQuery for this.
addEvents(window, {
	load: [ init, onResize ],
	resize: onResize
})
