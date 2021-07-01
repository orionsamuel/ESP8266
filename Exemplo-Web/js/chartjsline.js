//configuracao do grafico 1
var config = {
  type: 'line',
  data: {
    labels: ['January', 'February', 'March', 'April', 'May', 'June', 'July'],
    datasets: [{
        label: "Taxas de cliques - 2017",
        data: [5, 10, 5, 14, 20, 15, 6],
        borderWidth: 6,
        borderColor: 'rgba(77,166,253,0.85)',
        backgroundColor: 'transparent',
    },
    {
        label: "Taxa de cliques - 2018",
        data: [9, 14, 11, 6, 5, 4, 3],
        borderWidth: 6,
        borderColor: 'rgba(6,204,6,0.85)',
        backgroundColor: 'transparent',
    }]
},
  options: {
    responsive: true,
    title: {
      display: true,
      text: 'Chart.js Line Chart'
    },
    tooltips: {
      mode: 'index',
      intersect: false,
    },
    hover: {
      mode: 'nearest',
      intersect: true
    },
    scales: {
      xAxes: [{
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Month'
        }
      }],
      yAxes: [{
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Value'
        }
      }]
    }
  }
};

//cria o grafico 1
function createMyLine1() {
  var ctx = document.getElementById('canvas').getContext('2d');
  window.myLine = new Chart(ctx, config);
};