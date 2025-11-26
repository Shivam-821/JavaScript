let label = document.getElementById('label')
let shoppingCart = document.getElementById('shopping-cart')

let basket = JSON.parse(localStorage.getItem("data")) || []
console.log(basket)


let calculation = () => {
    let totalQuantity;
    let cartQuantity = document.getElementById('cartTotalItem')
    if(basket !== null){
        totalQuantity = basket.reduce((total, basItem) => total + basItem.item, 0)

        cartQuantity.innerHTML = totalQuantity
    }
    else return;
}


window.onload = () => {
    calculation()
}
let generateCartItem = () => {
    if(basket.length !== 0){
        console.log(basket.length)
        return (shoppingCart.innerHTML = basket.map((basItem) => {
            let {id, item} = basItem
            let itemDetails = itemsList.find((item) => item.id === id) || []
            let {name, img, price} = itemDetails
            let indiPrice = item * price
            return `
            <div class="cart-item" id=${id}>
                <div id="images-photo">
                <img width="85" src=${img} alt="item-img">
                </div>
                <div id="cart-item-details" class="cart-item-details">
                    <div class="item-name">
                        ${name} <span style="background-color: black; color: white; padding: 3px; border-radius: 5px;">$${price}</span>
                        <span onClick="deleteItem('${id}')" class="x" style="margin-left: 17px;">X</span>
                    </div>
                    <div class="plus-minus">
                    <b class="minus-cart" onClick="removeItem('${id}')">–</b> <span id="qnt-${id}">${item}</span> <b class="plus-cart" onClick="addItem('${id}')">+</b>
                    </div>
                    <div class="T-price" id="T-price-${id}">$${indiPrice}</div>
                </div>
            </div> 
            `
        }).join(""));
    }
    else{
        shoppingCart.innerHTML = ``
        label.innerHTML = `
        <h2>Cart is Empty</h2>
        <a href="index.html">
            <button class="HomeButton">Back to home</button>
        </a>
        `
    }
    totalBill()
}

generateCartItem()

const clearCart = () => {
    basket = []
    localStorage.setItem("data", JSON.stringify(basket))
    generateCartItem()
    calculation()
}

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
    generateCartItem()
}

let update = (id) => {
    let findItem = basket.find((item) => item.id === id)
    document.getElementById(`qnt-${id}`).innerHTML = findItem.item
    calculation()
    totalBill()
    individualItemPrice(id)
}

const totalBill = () => {
    let billAmount = 0;

    if(basket !== null){
        billAmount = basket.reduce((total, basItem) => {
            let { id, item } = basItem;
            let itemDet = itemsList.find((x) => x.id === id);
            return total + (itemDet.price * item);
        }, 0);
    }
    console.log(billAmount)
    document.getElementById("totalBill").innerHTML = `Total Bill: $${billAmount}`
}

totalBill()

const deleteItem = (id) => {
    basket = basket.filter((item) => item.id !== id)
    localStorage.setItem("data", JSON.stringify(basket))
    generateCartItem()
    totalBill()
    calculation()
}

const individualItemPrice = (id) => {
    let singleItem = basket.find((item) => item.id === id)
    if(singleItem){
        let itemL = itemsList.find((x) => x.id === id)
        if(itemL){
            document.getElementById(`T-price-${id}`).innerHTML = `$${singleItem.item * itemL.price}`
        } else return;
    } else return;    
}