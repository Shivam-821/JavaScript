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
        e.preventDefault();
        this.classList.remove("hover-over");
        if (draggedElement) {
            this.appendChild(draggedElement);
        }
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

// addTaskBtn.addEventListener("click", function () {
//     const taskTitle = document.querySelector("input").value;
//     const taskDescription = document.querySelector("textarea").value;
//     console.log(taskTitle, ":", taskDescription)
//     const task = document.createElement("div")
//     task.classList.add("task")
//     task.setAttribute("draggable", "true")
//     task.innerHTML = `
//     <div class="heading">${taskTitle}</div>
//     <div class="descrp">${taskDescription}</div>
//     <button class="delete-btn">Delete</button>
//     `
//     TodoTask.appendChild(task)
//     modal.classList.remove("active")
//     document.querySelector("input").value = ""
//     document.querySelector("textarea").value = ""
// })

// deleteBtn.forEach(btn => {
//     btn.addEventListener("click", function () {
//         this.parentElement.remove();
//     });
// });