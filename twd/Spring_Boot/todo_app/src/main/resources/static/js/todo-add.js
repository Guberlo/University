let script = document.currentScript;
$(document).ready(function() {
    var $form = $("#add-form");
    var request = {};
    $form.on('submit', function(e) {
      e.preventDefault(); // stop default form submission
      request['username'] = script.getAttribute('username'); 
      request['description'] = document.getElementById('description').value;
      request['date'] = document.getElementById('date').value;
      $.ajax({  // form submission via ajax
        url: $form.attr('action'), // form submission url
        type: 'POST',
        contentType:'application/json;charset=utf-8', // request type
        dataType: 'json', // data type
        data: JSON.stringify(request), // get all data from the form
        success: function(result) {
          console.log(result);
          alert('Todo added!')
          window.location.href = "/todo-list";
        },
        error: function(xhr, resp, text) { // response back from server in case of failure 
          console.log(xhr, resp, text);
          console.log('Data: ' + JSON.stringify(request));
        }
      })
    });
  });