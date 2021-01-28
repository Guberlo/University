@extends('layout')

@section('content')

<h1>Insert your painting in the repository!</h1>
<form method="POST" action="/paintings">
    @csrf
    <div style="margin-bottom: 1em">
        Author: <input type="text" name="author" placeholder="Insert author name" required>
    </div>

    <div style="margin-bottom: 1em">
        Museum: <input type="text" name="museum" placeholder="Insert the museum" required>
    </div>

    <div style="margin-bottom: 1em">
        Title: <input type="text" name="title" placeholder="Insert the title" required> 
    </div>

    <div style="margin-bottom: 1em">
        Description: <input type="text" name="description" placeholder="Insert the description (optional)"> 
    </div>

    <div style="margin-bottom: 1em">
        Year: <input type="text" name="year" placeholder="Insert the year of creation" required> 
    </div>

    <div>
        <input type="submit" name="submit" value="Submit">
    </div>

    @error
        {{ $message }}
    @enderror
</div>
</form>
    
@endsection