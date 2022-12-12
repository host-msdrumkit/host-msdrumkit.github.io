

$(document).ready(function(){
  $('#dkit').mapster({
    staticState: false,
    scaleMap: true,
    areas: [
      {
        key: "wood"// causes the mask to be included when this area is highlighted
      },
      {
        key: "piezomask",
        isMask: true                     // causes the inner circle to be treated as a mask, but only                                 // in the context of the "outer-circle-mask" group
      }
  // no special options needed for "inner-circle" - we want it to be treated normally on mouseover
  ]
  });
});
