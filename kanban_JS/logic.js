const ProgressTask = document.getElementById("progress")
const DoneTask = document.getElementById("done")
const TodoTask = document.getElementById("todo")
const addBtn = document.getElementById("kanban-btn");
const taskDiv = document.querySelectorAll(".task")

let draggedElement = null;


// draging the div from one board to another
taskDiv.forEach(task => {
    task.addEventListener("drag", function (e) {
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
        this.classList.remove("hover-over")
        this.appendChild(draggedElement);
    })
}

addDragEventsOnColumn(TodoTask)
addDragEventsOnColumn(ProgressTask)
addDragEventsOnColumn(DoneTask)



