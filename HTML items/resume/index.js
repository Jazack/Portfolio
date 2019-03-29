var contents = document.getElementsByClassName("myContent");
var places = document.getElementsByClassName("place");
var dates = document.getElementsByClassName("date");
var positions = document.getElementsByClassName("position");
var dutys = document.getElementsByClassName("duty");
var locations = document.getElementsByClassName("location");
var levels = document.getElementsByClassName("level");

// displayFromJson
function displayFromJson(resume) {
var layer = 0;
//
$('.name').html("<h1>" + Object.values(resume[layer][0]) + "</h1>");
$('.cell').text(Object.values(resume[layer][1]));
$('.email').text(Object.values(resume[layer][2]));
layer++;
$('#accomp').text("Accomplishments");
$('#technical').text("Technical Skills");
$('#languages').text("Languages");
$('#jobExperience').text("Job Experience");
$('#education').text("Education");
$(`.myContent:eq(0)`).html(resume[layer][0] + '<br />'+ resume[layer][1]);
layer++;

// loop for technical skills
for(var i = 0; i < 5; i++)
  $(`.myContent:eq(1)`).append(resume[layer][i] + '<br />');  
layer++;

$(`.myContent:eq(2)`).html(resume[layer][0] + '<br />'+ resume[layer][1]);
layer++;

// for loop work
for(var i = 0; i < resume[layer].length; i++) {
  $(`.place:eq(${i})`).html(resume[layer][i].myPlace);
  $(`.date:eq(${i})`).html(resume[layer][i].myDate);
  $(`.position:eq(${i})`).html("<b>" + resume[layer][i].myPosition + "</b>");
  $(`.location:eq(${i})`).html(resume[layer][i].myLocation);
  $(`.duty:eq(${i})`).html(resume[layer][i].myDuty);
}
layer++

// for loop education
for(var i = 0; i < resume[layer].length; i++) {
  $(`.place:eq(${i+3})`).html(resume[layer][i].myPlace);
  $(`.date:eq(${i+3})`).html(resume[layer][i].myDate);
  $(`.level:eq(${i})`).html("<b>" + resume[layer][i].myLevel + "</b>");
  $(`.location:eq(${i+3})`).html(resume[layer][i].myLocation);
}}// end of displayFromJson

var resume;
//$(document).getReady;
$.getJSON('resume.json', function(data) {
  resume = data;
displayFromJson(resume);
});

$('.myHeadline').click(function() {
  $(`.myContent:visible`).toggle();
  $(this).next().toggle();
})

$(document).ready(function(){
  $(`.myContent:visible`).toggle();
  $(`#start`).toggle();
})
;
