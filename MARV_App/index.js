let slider = document.getElementById("test_slider");
let output = document.getElementById("slider_output_val");

output.innerHTML = slider.value;

slider.oninput = function () {
    output.innerHTML = this.value;
}
