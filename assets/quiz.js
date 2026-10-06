// Quiz reutilizable para todas las lecciones.
//
// Uso en el HTML:
//   <div class="quiz">
//     <div class="pregunta" data-correcta="2" data-explica="Por qué es la 2...">
//       <p>Enunciado</p>
//       <div class="opciones">
//         <button>Opción 0</button><button>Opción 1</button><button>Opción 2</button>
//       </div>
//     </div>
//     <p class="marcador"></p>
//   </div>
//   <script src="../assets/quiz.js"></script>
//
// Al pulsar una opción: se marca bien/mal, se bloquea la pregunta y se
// muestra la explicación. El marcador cuenta aciertos al primer intento.

(function () {
  document.querySelectorAll(".quiz").forEach(function (quiz) {
    var preguntas = quiz.querySelectorAll(".pregunta");
    var marcador = quiz.querySelector(".marcador");
    var respondidas = 0;
    var aciertos = 0;

    function actualizarMarcador() {
      if (!marcador) return;
      marcador.textContent = respondidas === preguntas.length
        ? "Resultado: " + aciertos + " de " + preguntas.length +
          (aciertos === preguntas.length ? " — perfecto." : " — repasa las que fallaste y vuelve mañana.")
        : "Respondidas " + respondidas + " de " + preguntas.length + ".";
    }

    preguntas.forEach(function (p) {
      var correcta = parseInt(p.dataset.correcta, 10);
      var botones = p.querySelectorAll(".opciones button");
      var caja = document.createElement("div");
      caja.className = "respuesta";
      p.appendChild(caja);

      botones.forEach(function (b, i) {
        b.type = "button";
        b.addEventListener("click", function () {
          var acierto = i === correcta;
          botones.forEach(function (o) { o.disabled = true; });
          botones[correcta].classList.add("correcta");
          if (!acierto) b.classList.add("incorrecta");
          caja.innerHTML = (acierto ? "<strong>Correcto.</strong> " : "<strong>No.</strong> ") +
            (p.dataset.explica || "");
          caja.classList.add("visible");
          respondidas++;
          if (acierto) aciertos++;
          actualizarMarcador();
        });
      });
    });
    actualizarMarcador();
  });
})();
