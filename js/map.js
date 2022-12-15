

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

  $('#drumkit').mapster({
    isSelectable: false,
    scaleMap: true,
    fillColor: "33CC33",
    mapKey: 'alt',
    areas: [
      {key : 'croc', fillColor : "d42e16", fillOpacity : 0.025}
    ]

  });
});
