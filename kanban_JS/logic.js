const ProgressTask = document.getElementById("progress")
const DoneTask = document.getElementById("done")
const TodoTask = document.getElementById("todo")
const addBtn = document.getElementById("kanban-btn");
const taskDiv = document.querySelectorAll(".task");
const modal = document.getElementById("modal");
const addButton = document.getElementById("kanban-add-btn");
const addTaskBtn = document.getElementById("add-task-btn");
const deleteBtn = document.querySelectorAll(".delete-btn")

let draggedElement = null;
let tasksData = {};

const columns = [TodoTask, ProgressTask, DoneTask]

// functions to stop repeating code
function countTasks(column){
    const count = column.querySelectorAll(".task").length;
    const spanElement = column.querySelector("span");
    if (spanElement) {
        spanElement.textContent = count;
    }
}

function saveTasksData(column) {
    tasksData[column.id] = Array.from(column.querySelectorAll(".task")).map(task => {
        return {
            title: task.querySelector(".heading").textContent,
            description: task.querySelector(".descrp").textContent,
        }
    })

    localStorage.setItem("tasksData", JSON.stringify(tasksData))
}
 
function creatingTasksDiv(task, column) {
    const taskDiv = document.createElement("div")
    taskDiv.classList.add("task")
    taskDiv.setAttribute("draggable", "true")
    taskDiv.innerHTML = `
    <div class="heading">${task.title}</div>
    <div class="descrp">${task.description}</div>
    <button class="delete-btn">Delete</button>
    `
    column.appendChild(taskDiv)
    taskDiv.addEventListener("drag", () => {
        draggedElement = taskDiv;
    })
}

const localTask = localStorage.getItem("tasksData")
if (localTask) {
    tasksData = JSON.parse(localTask)

    for (const col in tasksData) {
        const column = document.getElementById(col)
        tasksData[col].forEach(task => {
            creatingTasksDiv(task, column)
        })

        countTasks(column)
    }
}

function addDragEventsOnColumn(column) {
    column.addEventListener("dragenter", function (e) {
        this.classList.add("hover-over")
    })

    column.addEventListener("dragleave", function (e) {
        this.classList.remove("hover-over")
    })

    column.addEventListener("dragover", function (e) {
        e.preventDefault();
    })

    column.addEventListener("drop", function (e) {
        // e.preventDefault();
        this.classList.remove("hover-over");
        if (draggedElement) {
            this.appendChild(draggedElement);
        }

        columns.forEach(column => {
            countTasks(column)
            saveTasksData(column)
        })
    });
}

addDragEventsOnColumn(TodoTask)
addDragEventsOnColumn(ProgressTask)
addDragEventsOnColumn(DoneTask)

// adding new task
addButton.addEventListener("click", function () {
    modal.classList.add("active")
})

const modalBlur = document.querySelector(".modal-blur")
modalBlur.addEventListener("click", function () {
    modal.classList.remove("active")
})

addTaskBtn.addEventListener("click", function () {
    const taskTitle = document.querySelector("#task-heading").value;
    const taskDescription = document.querySelector("#task-descrp").value;
    // console.log(taskTitle, ":", taskDescription)
    creatingTasksDiv({
        title: taskTitle,
        description: taskDescription
    }, TodoTask)
    modal.classList.remove("active")
        
    columns.forEach(column => {
        countTasks(column)
        saveTasksData(column)
    })

    document.querySelector("#task-heading").value = ""
    document.querySelector("#task-descrp").value = ""
})

// deleteBtn.forEach(btn => {
//     btn.addEventListener("click", function () {
//         this.parentElement.remove();
//     });
// });