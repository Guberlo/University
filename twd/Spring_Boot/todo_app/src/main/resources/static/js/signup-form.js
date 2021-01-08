$(document).ready(function() {
    var $form = $("#signup-form");
    var request = {};
    $form.on('submit', function(e) {
      e.preventDefault(); // stop default form submission 
      request['name'] = document.getElementById('name').value;
      request['username'] = document.getElementById('username').value;
      request['email'] = document.getElementById('email').value;
      request['password'] = document.getElementById('password').value;
      $.ajax({  // form submission via ajax
        url: $form.attr('action'), // form submission url
        type: 'POST',
        contentType:'application/json;charset=utf-8', // request type
        dataType: 'json', // data type
        data: JSON.stringify(request), // get all data from the form
        success: function(result) {
          console.log(result);
          window.location.href = "/login"; // response back from server in case of success
        },
        error: function(xhr, resp, text) { // response back from server in case of failure 
          console.log(xhr, resp, text);
          console.log('Data: ' + JSON.stringify(request));
        }
      })
    });
  });