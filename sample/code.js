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
{ data: { id: '20', name: 'T'} },
{ data: { id: '0', name: '$'} },
{ data: { id: '3', name: 'G'} },
{ data: { id: '36', name: 'T'} },
{ data: { id: '58', name: 'C'} },
{ data: { id: '9', name: 'A'} },
{ data: { id: '75', name: 'G'} },
{ data: { id: '50', name: 'C'} },
{ data: { id: '27', name: 'G'} },
{ data: { id: '18', name: 'C'} },
{ data: { id: '41', name: 'A'} },
{ data: { id: '68', name: 'T'} },
], edges: [
{ data: { source: '20', target: '27', strength: 10 } },
{ data: { source: '0', target: '3', strength: 10000 } },
{ data: { source: '3', target: '9', strength: 10000 } },
{ data: { source: '36', target: '41', strength: 10000 } },
{ data: { source: '58', target: '68', strength: 1000 } },
{ data: { source: '9', target: '20', strength: 10 } },
{ data: { source: '9', target: '18', strength: 1000 } },
{ data: { source: '75', target: '85', strength: 10000 } },
{ data: { source: '50', target: '58', strength: 10 } },
{ data: { source: '27', target: '36', strength: 1000 } },
{ data: { source: '18', target: '36', strength: 10 } },
{ data: { source: '18', target: '27', strength: 100 } },
{ data: { source: '41', target: '50', strength: 10 } },
{ data: { source: '41', target: '75', strength: 10 } },
{ data: { source: '41', target: '58', strength: 100 } },
{ data: { source: '68', target: '75', strength: 1000 } },
]},
  
  ready: function(){
    window.cy = this;
    
    // giddy up
  }
});

}); // on dom ready
