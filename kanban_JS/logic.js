const ProgressTask = document.getElementById("progress")
const DoneTask = document.getElementById("done")
const TodoTask = document.getElementById("todo")
const addBtn = document.getElementById("kanban-btn");
const taskDiv = document.querySelectorAll(".task")


// draging the div from one board to another
taskDiv.forEach(task => {
    task.addEventListener("drag", function (e) {
        console.log("drag", e)
    })
})

