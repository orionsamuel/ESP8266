//configuracao do grafico 2
var config_line2 = {
  type: 'line',
  data: {
    labels: [],
    datasets: [{
      label: 'Temperatura',
      data: [],
      borderWidth: 6,
      borderColor: 'rgba(255,0,0,0.85)',
      backgroundColor: 'transparent',
    },
    {
      label: 'Umidade',
      data: [],
      borderWidth: 6,
      borderColor: 'rgba(56,176,222,0.85)',
      backgroundColor: 'transparent',
    }]
  },
  options: {
    responsive: true,
    title: {
      display: true,
      text: 'Chart.js and Thingspeak Chart'
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
        type: 'time',
        ticks: {
          minRotation: 90,
          source: 'data'  
        },
        distribution: 'series',
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Sample'
        }
      }],
      yAxes: [{
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Values'
        }
      }]
    }
  }
};

/*cria o grafico myline2 com os ultimos valores enviados#
* para o thingspeak
*/
function createMyLine2() {
  var ctx = document.getElementById('canvas2').getContext('2d');
  window.myLine2 = new Chart(ctx, config_line2);
  getLastThingSpeakData();
};

/*
* requisita os ultimos dados enviados para o thingspeak
* e atualiza os valores no grafico
*/
function getLastThingSpeakData(){
  
  var channel_id = 998946; //id do canal
  var field_number1 = 1; //numero do field
  var field_number2 = 2; //numero do field
  var num_results = 10; //numero de resultados requisitados
  $.getJSON('https://api.thingspeak.com/channels/' + channel_id + '/fields/' + field_number1 + '.json?results=10', function(data) {
    // get the data point
    feeds = data.feeds;
    // imprime os feeds recebidos
    console.log(data.feeds)
    // intera em todos os feeds recebidos e os adiciona no grafico
    for (d in feeds)
    {
      //variavel config_line2.data.datasets[0].data eh equivalente ao eixo y
      config_line2.data.datasets[0].data.push(feeds[d].field1);
      //variavel config_line2.labels eh equivalente ao eixo x
      var x_date = new Date(feeds[d].created_at);
      config_line2.data.labels.push(x_date);
    }
    window.myLine2.update();
  });

  $.getJSON('https://api.thingspeak.com/channels/' + channel_id + '/fields/' + field_number2 + '.json?results=10', function(data) {
    // get the data point
    feeds = data.feeds;
    // imprime os feeds recebidos
    console.log(data.feeds)
    // intera em todos os feeds recebidos e os adiciona no grafico
    for (d in feeds)
    {
      //variavel config_line2.data.datasets[1].data eh equivalente ao eixo y
      config_line2.data.datasets[1].data.push(feeds[d].field2);
      //variavel config_line2.labels eh equivalente ao eixo x
      var x_date = new Date(feeds[d].created_at);
      config_line2.data.labels.push(x_date);
    }
    window.myLine2.update();
  });
}
  