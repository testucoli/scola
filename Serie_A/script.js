
let img; 
let player;
let select, selected;


function Load() {
  let select, option;

  select = document.getElementById("players");

  for (let i = 0; i != 4; i++) {
    option = document.createElement("option");
    option.text = listateams.teams[i].name;
    option.value = listateams.teams[i].id;
    select.add(option);
  }
}

let j;
let htmlp;
var team_id;
let player_id; 
let buttons = document.getElementById("buttons");
function Run() {

  const existingPlayerButtons = document.querySelectorAll('.plyr');
  existingPlayerButtons.forEach(button => button.remove());
  document.getElementById("carriera").innerHTML = "";
  

  htmlp=1;
  select = document.getElementById("players");
  selected = select.value;

  for(var i=0; i!=listaplayers.players.length; i++) {

    team_id = listaplayers.players[i].team_id; 
      if(team_id == selected) {
        player_id = listaplayers.players[i].id;
 
        for (j = i; j < i + 3; j++) {
        const button = document.createElement("button");
        button.id = "player" + htmlp;
        button.className = "plyr";
        buttons.appendChild(button);
        player = document.getElementById("player"+htmlp);
        player.innerHTML = (listaplayers.players[j].name + " " + listaplayers.players[j].surname + " " + "<br>");
        const image = document.createElement("img");
        image.src = listaplayers.players[j].image;
        player.appendChild(image);
        button.onclick = function() {
          Career(this.id, selected);
        };
        htmlp++;
        }
        break;
      }
        
       }   
  }

  function Career(id, selected) {
    for(var i=0; i!=listacarrers.careers.length; i++) {

      team_id = listacarrers.careers[i].team_id; 
        if(team_id == selected) {
          player_id = listacarrers.careers[i].id;
          for (j = i; j < i + 3; j++) {
            if(parseInt(id.replace("player", "")) == listaplayers.players[j].id && listacarrers.careers[j].team_id == selected) {
              document.getElementById("carriera").innerHTML = "<hr>Anno Prime: " + listacarrers.careers[j].year + "<br>Partite: " + listacarrers.careers[j].games + "<br>Goal: " + listacarrers.careers[j].goals + "<br>Assist: " + listacarrers.careers[j].assists;
            }
            break;
          }
  }
}
  }

 

    