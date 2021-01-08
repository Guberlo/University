<%@ include file="common/header.jspf"%>
<%@ include file="common/navigation.jspf"%>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script type="text/javascript" src="/resources/js/todo-add.js" username=${username}></script>

<div class="container">
    <div class="row">
        <div class="col-md-6 col-md-offset-3">
            <div class="panel panel-primary">
                <div class="panel-heading">Hey ${username}, add a TODO</div>
                <div class="panel-body">
                    <form method="POST" action="/api/Todo" id="add-form">
                        <fieldset class="form-group">
                            <label>Description</label>
                            <input type="text" class="form-control" id="description" required="required"/>
                        </fieldset>

                        <fieldset class="form-group">
                            <label>Date</label>
                            <input type="text" class="form-control" id="date" required="required"/>
                        </fieldset>
                        
                        <button type="submit" class="btn btn-success">Submit</button>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>
<%@ include file="common/footer.jspf"%>