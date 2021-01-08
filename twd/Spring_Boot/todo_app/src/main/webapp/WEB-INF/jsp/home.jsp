<%@ include file="common/header.jspf"%>
<%@ include file="common/navigation.jspf"%>

<div class="container">

    <div class="panel panel-primary">
        <div class="panel-heading">Home</div>
        <div class="panel-body">
            Hi ${username}! Click the button below to manage your todos!
            <div>
                <a class="btn btn-primary" id="button-list" href="todo-list">Show List</a>
            </div>
        </div>
    </div>
</div>
<%@ include file="common/footer.jspf"%>