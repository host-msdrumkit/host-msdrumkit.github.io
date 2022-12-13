

$(document).ready(function(){
  $('#unaspad').mapster({
    isSelectable: false,
    scaleMap: true,
    fillColor: "990000",
    mapKey: 'alt',
    areas: [
      {
        mapKey: 'wood'
      }
    ]
  });
});


$(document).ready(function(){
  $('#aspad').mapster({
    isSelectable: false,
    scaleMap: true,
    fillColor: "008888",
    mapKey: 'alt',
    areas: [
      {
        mapKey: 'woodas'
      }
    ]
  });
});
