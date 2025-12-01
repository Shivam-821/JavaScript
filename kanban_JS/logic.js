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

// const localTask = localStorage.getItem("tasksData")
// if (localTask) {
//     tasksData = JSON.parse(localTask)
// }


// draging the div from one board to another
taskDiv.forEach(task => {
    task.addEventListener("dragstart", function (e) {
        // console.log("drag", e)
        draggedElement = this;
    })
})

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
           const count = column.querySelectorAll(".task").length;
           const spanElement = column.querySelector("span");
           if (spanElement) {
               spanElement.textContent = count;
           }
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
    const task = document.createElement("div")
    task.classList.add("task")
    task.setAttribute("draggable", "true")
    task.innerHTML = `
    <div class="heading">${taskTitle}</div>
    <div class="descrp">${taskDescription}</div>
    <button class="delete-btn">Delete</button>
    `
    TodoTask.appendChild(task)
    modal.classList.remove("active")
    task.addEventListener("drag", () => {
        draggedElement = task;
    })
        
    columns.forEach(column => {
        const tasks = column.querySelectorAll(".task");
        const spanElement = column.querySelector("span");
        spanElement.textContent = tasks.length;

        tasksData[column.id] = Array.from(tasks).map(task => { 
            return {
                title: task.querySelector(".heading").textContent,
                description: task.querySelector(".descrp").textContent,
            }
        })

        console.log(tasksData)
        localStorage.setItem("tasksData", JSON.stringify(tasksData))
    })

    
    
    document.querySelector("#task-heading").value = ""
    document.querySelector("#task-descrp").value = ""
})

// deleteBtn.forEach(btn => {
//     btn.addEventListener("click", function () {
//         this.parentElement.remove();
//     });
// });