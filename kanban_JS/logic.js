

// add todo-task
const addBtn = document.getElementById("kanban-btn");
const kanbanTodoTask = document.getElementById("kanban-todo-board")

addBtn.addEventListener("click", function () {
    kanbanTodoTask.innerHTML += `
    <div class="task">
        <input class="heading" type="text" placeholder="Enter Task Heading"/>
        <input class="descrp" type="text" placeholder="Enter Task Description"/>
        <button>Delete</button>
    </div>
    `
})

// delete todo-task
const deleteBtn = document.querySelector(".task button")

deleteBtn.addEventListener("click", function (e) {
    e.target.parentElement.remove()
})

