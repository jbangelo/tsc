window.onload = function() {
	$("#datepicker").datepicker({autoSize: true});
	$("#timepicker").timepicker();

	var timezone = jstz.determine();
	$("#tzField").val(timezone.name());
}


