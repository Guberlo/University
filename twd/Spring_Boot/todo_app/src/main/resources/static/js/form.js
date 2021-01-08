$(document).ready(function() {
    var $form = $("#login-form");
    var request = {};
    $form.on('submit', function(e) {
      e.preventDefault(); // stop default form submission 
      request['username'] = document.getElementById('username').value;
      request['password'] = document.getElementById('password').value;
      $.ajax({  // form submission via ajax
        url: $form.attr('action'), // form submission url
        type: 'POST',
        contentType:'application/json;charset=utf-8', // request type
        dataType: 'json', // data type
        data: JSON.stringify(request), // get all data from the form
        success: function(result) {
          console.log(result);
          document.cookie = "token=" + result.token;
          window.location.href = "/home"; // response back from server in case of success
        },
        error: function(xhr, resp, text) { // response back from server in case of failure 
          console.log(xhr, resp, text);
          console.log('Data: ' + JSON.stringify(request));
        }
      })
    });
  });