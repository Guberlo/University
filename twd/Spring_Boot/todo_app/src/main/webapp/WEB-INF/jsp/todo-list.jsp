<%@ include file="common/header.jspf"%>
<%@ include file="common/navigation.jspf"%>
<script type="text/javascript" src="/resources/js/todo-list.js"></script>

<div class="container">
    <div>
        <a type="button" class="btn btn-primary btn-md" href="/todo-add">Add something TODO</a>
    </div>
    <br>
    <div class="panel panel-primary">
        <div class="panel-heading">
            <h3>${username}'s Todo List</h3>
        </div>
        <div class="panel-body">
            <table class="table table-striped">
                <thead>
                    <tr>
                        <th width="40%">Description</th>
                        <th width="40%">Date</th>
                        <th width="20%"></th>
                    </tr>
                </thead>
                <tbody id="tbody-list">
                </tbody>
            </table>
        </div>
    </div>
</div>
<%@ include file="common/footer.jspf"%>