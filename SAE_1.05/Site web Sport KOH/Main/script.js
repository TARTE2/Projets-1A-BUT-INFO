// MENU

function toggleMenu() {
    const navMobile = document.querySelector('.nav-mobile');
    const mobileOverlay = document.querySelector('.mobile-overlay');

    if (navMobile.classList.contains('active')) {
        navMobile.classList.remove('active');
        mobileOverlay.classList.remove('active');
        closeSubmenu();
    } else {
        navMobile.classList.add('active');
        mobileOverlay.classList.add('active');
    }

}

function openSubmenu() {
    const submenu = document.querySelector('.submenu');
    submenu.classList.add('active');
    console.log("ouvre");
}

function closeSubmenu() {
    const submenu = document.querySelector('.submenu');
    submenu.classList.remove('active');
    console.log("ferme");
}

function openSubmenuS() {
    const submenu = document.querySelector('.submenuS');
    submenu.classList.add('active');
}

function closeSubmenuS() {
    const submenu = document.querySelector('.submenuS');
    submenu.classList.remove('active');
}

function openSubmenuL() {
    const submenu = document.querySelector('.submenuL');
    submenu.classList.add('active');
}

function closeSubmenuL() {
    const submenu = document.querySelector('.submenuL');
    submenu.classList.remove('active');
}

function openSubmenuJ() {
    const submenu = document.querySelector('.submenuJ');
    submenu.classList.add('active');
}

function closeSubmenuJ() {
    const submenu = document.querySelector('.submenuJ');
    submenu.classList.remove('active');
}

function openSubmenuC() {
    const submenu = document.querySelector('.submenuC');
    submenu.classList.add('active');
}

function closeSubmenuC() {
    const submenu = document.querySelector('.submenuC');
    submenu.classList.remove('active');
}

// TABS
var tabLink = document.querySelectorAll('.tabs a');

for (var i = 0; i < tabLink.length; i++) {
    tabLink[i].addEventListener('click', function(event) {
        event.preventDefault();
        document.querySelector('.tabs-content__tab.active').classList.remove('active');
        document.querySelector('.tabs a.active').classList.remove('active');
        event.target.classList.add('active');
        document.querySelector(`.${event.target.dataset.open}`).classList.add('active');
    });
}