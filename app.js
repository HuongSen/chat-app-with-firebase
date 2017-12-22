(function () {
    // Initialize Firebase
  var config = {
    apiKey: "AIzaSyB3hxXHxAqvF9h2a9jlkJMQ_9x-keYfPEE",
    authDomain: "quickchat-328af.firebaseapp.com",
    databaseURL: "https://quickchat-328af.firebaseio.com",
    projectId: "quickchat-328af",
    storageBucket: "quickchat-328af.appspot.com",
    messagingSenderId: "1020261149865"
  };
  firebase.initializeApp(config);

  //get elements
  const txtEmail = document.getElementById('txtEmail');
  const txtPassword = document.getElementById('txtPassword');
  const btnLogin = document.getElementById('btnLogin');

  // Add Login event
  btnLogin.addEventListener('click', e => {
    const email = txtEmail.value;
    const pass = txtPassword.value;
    const auth = firebase.auth();
    //Sign in
    const promise = auth.signInWithEmailAndPassword(email, pass);
    promise.catch(e => console.log(e.message));

  });
}());
