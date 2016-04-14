$(function(){ // on dom ready

$('#cy').cytoscape({
  layout: {
    name: 'cose',
    padding: 10
  },
  
  style: cytoscape.stylesheet()
    .selector('node')
      .css({
        'width': 'mapData(weight, 40, 80, 20, 60)',
        'content': 'data(name)',
        'text-valign': 'center',
        'text-outline-width': 2,
        'color': '#fff'
      })
    .selector(':selected')
      .css({
        'border-width': 3,
        'border-color': '#333'
      })
    .selector('edge')
      .css({
        'opacity': 0.666,
        'width': 'mapData(strength, 70, 100, 2, 6)',
        'target-arrow-shape': 'triangle',
        'source-arrow-shape': 'circle',
      })
    .selector('edge.questionable')
      .css({
        'line-style': 'dotted',
        'target-arrow-shape': 'diamond'
      })
    .selector('.faded')
      .css({
        'opacity': 0.25,
        'text-opacity': 0
      }),
elements: {
nodes: [
{ data: { id: '2057', name: 'A'} },
{ data: { id: '1033', name: 'A'} },
{ data: { id: '2089', name: 'A'} },
{ data: { id: '1065', name: 'A'} },
{ data: { id: '0', name: '$'} },
{ data: { id: '3', name: 'G'} },
{ data: { id: '1044', name: 'C'} },
{ data: { id: '9', name: 'A'} },
{ data: { id: '66', name: 'T'} },
{ data: { id: '20', name: 'C'} },
{ data: { id: '52', name: 'C'} },
{ data: { id: '75', name: 'G'} },
{ data: { id: '27', name: 'G'} },
{ data: { id: '60', name: 'C'} },
{ data: { id: '34', name: 'T'} },
{ data: { id: '18', name: 'T'} },
{ data: { id: '41', name: 'A'} },
], edges: [
{ data: { source: '2057', target: '20', strength: 100 } },
{ data: { source: '1033', target: '1044', strength: 1000 } },
{ data: { source: '2089', target: '60', strength: 100 } },
{ data: { source: '1065', target: '75', strength: 10 } },
{ data: { source: '0', target: '3', strength: 10000 } },
{ data: { source: '3', target: '2057', strength: 10000 } },
{ data: { source: '3', target: '1033', strength: 10000 } },
{ data: { source: '3', target: '9', strength: 10000 } },
{ data: { source: '1044', target: '27', strength: 100 } },
{ data: { source: '9', target: '18', strength: 10 } },
{ data: { source: '66', target: '75', strength: 1000 } },
{ data: { source: '20', target: '34', strength: 10 } },
{ data: { source: '52', target: '60', strength: 10 } },
{ data: { source: '75', target: '85', strength: 10000 } },
{ data: { source: '27', target: '34', strength: 1000 } },
{ data: { source: '60', target: '66', strength: 1000 } },
{ data: { source: '34', target: '2089', strength: 10000 } },
{ data: { source: '34', target: '1065', strength: 10000 } },
{ data: { source: '34', target: '41', strength: 10000 } },
{ data: { source: '18', target: '27', strength: 10 } },
{ data: { source: '41', target: '52', strength: 10 } },
]},


  
  ready: function(){
    window.cy = this;
    
    // giddy up
  }
});

}); // on dom ready
