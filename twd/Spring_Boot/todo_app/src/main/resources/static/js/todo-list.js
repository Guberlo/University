document.addEventListener('DOMContentLoaded', getJsonData, false);

function getTokenFromCookie(token_key) {
    let token = document.cookie.match('(^|;)\\s*' + token_key + '\\s*=\\s*([^;]+)');
    return token ? token.pop() : '';
}

function getJsonData() {
    let json_url = '/api/users/Todo';

    // Build an AJAX request
    let request = new XMLHttpRequest();
    request.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
            let data = JSON.parse(this.responseText);
            insertTableData(data);
        }
    }

    request.open('GET', json_url, true);
    request.setRequestHeader('Authorization', getTokenFromCookie('token'));
    request.send();
}

function insertTableData(data) {
    let tbody = document.getElementById('tbody-list');
    data.forEach(function(todo) {
        let tr = document.createElement('tr');
        tr.innerHTML = '<td>' + todo.description + '</td>' +
                    '<td>' + todo.date + '</td>' +
                    '<td><a type="button" class="btn btn-success" \
                    href="/Todo" id="btn-update">Update</a></td>' +
                    '<td><a type="button" class="btn btn-warning" \
                    href="/Todo" id="btn-delete">Delete</a></td>';
        tbody.appendChild(tr);
    })
}