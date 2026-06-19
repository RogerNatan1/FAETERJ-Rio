// Dados iniciais estruturados para os pets
const defaultPets = [
  {
    id: 1,
    name: "Gato 1",
    icon: "fa-cat",
    color: "text-orange-500",
    bgLight: "bg-orange-100",
    actions: { feed: null, meds: null, litter: null, play: null },
  },
  {
    id: 2,
    name: "Gato 2",
    icon: "fa-cat",
    color: "text-slate-600",
    bgLight: "bg-slate-200",
    actions: { feed: null, meds: null, litter: null, play: null },
  },
  {
    id: 3,
    name: "Gato 3",
    icon: "fa-cat",
    color: "text-amber-700",
    bgLight: "bg-amber-100",
    actions: { feed: null, meds: null, litter: null, play: null },
  },
];

// Metadados das ações que mapeiam ícones e classes do CSS
const actionTypes = {
  feed: { label: "Alimentar", icon: "fa-bowl-food", colorClass: "bg-feed" },
  meds: { label: "Remédio", icon: "fa-pills", colorClass: "bg-meds" },
  litter: { label: "Higiene", icon: "fa-bath", colorClass: "bg-hygiene" },
  play: { label: "Brincar", icon: "fa-baseball", colorClass: "bg-play" },
};

// Inicialização de dados: busca do LocalStorage ou define o array inicial padrão
let petsData =
  JSON.parse(localStorage.getItem("petTrackerData")) || defaultPets;

function saveToLocalStorage() {
  localStorage.setItem("petTrackerData", JSON.stringify(petsData));
}

// Algoritmo para calcular e formatar o tempo de forma amigável (UX)
function formatTimestamp(isoString) {
  if (!isoString)
    return '<span class="text-slate-400 italic">Pendente hoje</span>';

  const date = new Date(isoString);
  const now = new Date();
  const diffMs = now - date;
  const diffMins = Math.floor(diffMs / 60000);
  const diffHours = Math.floor(diffMins / 60);

  const timeStr = date.toLocaleTimeString("pt-BR", {
    hour: "2-digit",
    minute: "2-digit",
  });

  if (diffMins < 1)
    return `<span class="text-green-600 font-semibold">Agora mesmo</span>`;
  if (diffMins < 60)
    return `<span class="text-green-600 font-semibold">Há ${diffMins} min</span>`;
  if (diffHours < 24 && date.getDate() === now.getDate())
    return `<span class="text-slate-600">Hoje às ${timeStr}</span>`;
  if (diffHours < 48 && date.getDate() === now.getDate() - 1)
    return `<span class="text-slate-500">Ontem às ${timeStr}</span>`;

  return `<span class="text-slate-400">${date.toLocaleDateString("pt-BR")} às ${timeStr}</span>`;
}

// Registra o exato momento atual (ISO String) na ação do pet selecionado
function registerAction(petId, actionKey) {
  const petIndex = petsData.findIndex((p) => p.id === petId);
  if (petIndex > -1) {
    petsData[petIndex].actions[actionKey] = new Date().toISOString();
    saveToLocalStorage();
    renderDashboard();
    showToast(
      `${actionTypes[actionKey].label} registrado para ${petsData[petIndex].name}!`,
    );
  }
}

// Reseta o histórico de cuidados voltando ao estado original limpo
function resetAll() {
  if (confirm("Tem certeza que deseja apagar todos os registros de hoje?")) {
    petsData = JSON.parse(JSON.stringify(defaultPets));
    saveToLocalStorage();
    renderDashboard();
    showToast("Todos os registros foram resetados.");
  }
}

// Controla a animação de entrada e saída do aviso em tela (Toast)
function showToast(message) {
  const toast = document.getElementById("toast");
  document.getElementById("toast-message").textContent = message;

  toast.classList.remove("translate-y-20", "opacity-0");

  setTimeout(() => {
    toast.classList.add("translate-y-20", "opacity-0");
  }, 3000);
}

// Função de renderização principal: reconstrói dinamicamente os cards na tela (DOM Manipulation)
function renderDashboard() {
  const container = document.getElementById("pets-container");
  container.innerHTML = "";

  petsData.forEach((pet) => {
    const card = document.createElement("div");
    card.className =
      "pet-card bg-white rounded-2xl p-6 border border-slate-100 flex flex-col h-full";

    let html = `
            <div class="flex items-center justify-between gap-4 mb-6 border-b border-slate-100 pb-4">
                <div class="flex items-center gap-4">
                  <div class="w-16 h-16 rounded-full flex items-center justify-center text-3xl ${pet.bgLight} ${pet.color}">
                      <i class="fa-solid ${pet.icon}"></i>
                  </div>
                  <div>
                      <h2 class="text-xl font-bold text-slate-800">${pet.name}</h2>
                      <p class="text-sm text-slate-500">Status: <span class="text-green-500"><i class="fa-solid fa-heart"></i> Saudável</span></p>
                  </div>
                </div>
                <button
                  onclick="removePet(${pet.id})"
                  class="text-slate-400 hover:text-red-500 transition-colors"
                  title="Remover pet"
                >
                  <i class="fa-solid fa-trash"></i>
                </button>
            </div>
            <div class="grow space-y-4">
        `;

    Object.keys(actionTypes).forEach((key) => {
      const action = actionTypes[key];
      const lastDone = pet.actions[key];

      html += `
                <div class="flex items-center justify-between bg-slate-50 p-3 rounded-xl border border-slate-100">
                    <div class="flex flex-col">
                        <span class="font-semibold text-slate-700 text-sm flex items-center gap-2">
                            <i class="fa-solid ${action.icon} w-4"></i> ${action.label}
                        </span>
                        <span class="text-xs mt-1">${formatTimestamp(lastDone)}</span>
                    </div>
                    <button 
                        onclick="registerAction(${pet.id}, '${key}')"
                        class="action-btn w-10 h-10 rounded-full text-white flex items-center justify-center shadow-sm ${action.colorClass}"
                        title="Registrar ${action.label}"
                    >
                        <i class="fa-solid fa-plus"></i>
                    </button>
                </div>
            `;
    });

    html += `</div>`;
    card.innerHTML = html;
    container.appendChild(card);
  });
}

function getNextPetId() {
  return petsData.reduce((maxId, pet) => Math.max(maxId, pet.id), 0) + 1;
}

function addPet() {
  const defaultName = `Pet ${petsData.length + 1}`;
  const petName = prompt("Digite o nome do novo pet:", defaultName);
  if (!petName) return;

  const newPet = {
    id: getNextPetId(),
    name: petName.trim() || defaultName,
    icon: "fa-cat",
    color: "text-slate-600",
    bgLight: "bg-slate-200",
    actions: { feed: null, meds: null, litter: null, play: null },
  };

  petsData.push(newPet);
  saveToLocalStorage();
  renderDashboard();
  showToast(`Pet ${newPet.name} adicionado!`);
}

function removePet(petId) {
  const petIndex = petsData.findIndex((pet) => pet.id === petId);
  if (petIndex === -1) return;

  if (!confirm(`Deseja remover ${petsData[petIndex].name}?`)) return;

  petsData.splice(petIndex, 1);
  saveToLocalStorage();
  renderDashboard();
  showToast(`${petsData[petIndex]?.name || "Pet"} removido.`);
}

function resetAll(isAuto = false) {
  if (
    !isAuto &&
    !confirm("Tem certeza que deseja apagar todos os registros de hoje?")
  ) {
    return;
  }

  petsData = JSON.parse(JSON.stringify(defaultPets));
  saveToLocalStorage();
  renderDashboard();

  if (isAuto) {
    const today = new Date().toISOString().split("T")[0];
    localStorage.setItem("petTrackerAutoResetDate", today);
    showToast("Dados reiniciados automaticamente às 4h.");
  } else {
    showToast("Todos os registros foram resetados.");
  }
}

function checkDailyAutoReset() {
  const now = new Date();
  const today = now.toISOString().split("T")[0];
  const lastAutoResetDate = localStorage.getItem("petTrackerAutoResetDate");

  if (lastAutoResetDate === today) {
    return;
  }

  if (now.getHours() > 4 || (now.getHours() === 4 && now.getMinutes() >= 0)) {
    resetAll(true);
  }
}

// Primeira execução ao carregar a página
checkDailyAutoReset();
renderDashboard();

// Atualização passiva a cada minuto para manter as tags de tempo (Ex: "Há 2 min") sempre precisas
setInterval(() => {
  renderDashboard();
  checkDailyAutoReset();
}, 60000);
