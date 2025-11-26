let shop = document.getElementById("shop")

// console.log(shop)


let basket = JSON.parse(localStorage.getItem("data")) || []

let generateShop = () => {
    return (shop.innerHTML= itemsList.map((item) => {
        let {id, name, price, desc, img} = item // de-structure of object
        let search = basket.find((item) => item.id === id) || []
        
        return `
            <div id=${id} class="item">
                <img width="220" height='190' src=${img} alt="">
                <div class="details">
                    <h3>${name}</h3>
                    <p>${desc}</p>
                    <div class="price-quantity">
                        <h2>$${price}</h2>
                        <div id="buttons">
                            <div 
                            onClick="removeItem('${id}')"
                            class="minus"  style="font-weight: 500; font-size: x-large;">
                                -
                            </div>
                            <div id=qnt-${id} class="quantity" style="font-weight: 500;
                            font-size: large;">${search.item === undefined? 0 : search.item}</div>
                            <div onClick="addItem('${id}')" class="add"    style="font-weight: 500;
                            font-size: x-large;">
                                +
                            </div>
                        </div>
                    </div>
                </div>
            </div>`
    }).join(""))  /* it is used to convert array into string */
}

generateShop()

/* +, - button functionality */

const itemQuantity = document.querySelector(".quantity")

let addItem = (id) => {
    // console.log(id)
    let findItem = basket.find((item) => item.id === id)
    if(findItem){
        findItem.item += 1;
    } else{
        basket.push({
            id: id,
            item: 1
        })
    }
    localStorage.setItem("data", JSON.stringify(basket))
    update(id)
}

let removeItem = (id) => {
    let findItem = basket.find((item) => item.id === id)
    if(findItem && findItem.item > 0){
        findItem.item -= 1;
    } else return;
    update(id)
    basket = basket.filter((basketItem) => basketItem.item !== 0) 
    localStorage.setItem("data", JSON.stringify(basket))
    
}

let update = (id) => {
    let findItem = basket.find((item) => item.id === id)
    document.getElementById(`qnt-${id}`).innerHTML = findItem.item
    calculation()
}


let calculation = () => {
    let totalQuantity;
    let cartQuantity = document.getElementById('cartTotalItem')
    if(basket !== null){
        totalQuantity = basket.map((basItem) => basItem.item).reduce((total, accu) => total+accu, 0)
        cartQuantity.innerHTML = totalQuantity
    }
    else return;
}


window.onload = () => {
    calculation()
}
