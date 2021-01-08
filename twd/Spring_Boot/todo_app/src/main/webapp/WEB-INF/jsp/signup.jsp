<html>

<head>
    <link href="//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" rel="stylesheet" id="bootstrap-css">
    <link href="resources/css/login.css" rel="stylesheet" id="login-css">
    <script src="//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js"></script>
    <script src="//cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script type="text/javascript" src="/resources/js/signup-form.js"></script>
    <title>Todo App</title>
</head>

<body>
    <div class="wrapper fadeInDown">
        <div class="login-header">
            <h3>Welcome to your TODO app!</h3>
        </div>
        <div id="formContent">

            <!-- Icon -->
            <div class="fadeIn first">
                <img src="https://upload.wikimedia.org/wikipedia/commons/9/99/Sample_User_Icon.png" id="icon" alt="User Icon" />
            </div>

            <form id="signup-form" action="/api/auth/signup" method="post">
                <input type="text" id="username" class="fadeIn second" name="login" placeholder="username" size="50">
                <input type="text" id="name" class="fadeIn third" name="login" placeholder="name" size="50">
                <input type="email" id="email" class="fadeIn fourth" name="login" placeholder="email@email.com" size="50">
                <input type="password" id="password" class="fadeIn fifth" name="login" placeholder="password" size="50">
                <input type="submit" class="fadeIn sixth" value="Sign Up">
            </form>
            <div id="formFooter">
                <a class="underlineHover" href="https://bootsnipp.com/snippets/dldxB">Login template found here</a>
              </div>

        </div>
    </div>
</body>

</html>