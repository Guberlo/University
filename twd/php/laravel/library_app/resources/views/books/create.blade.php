@extends('layout')

@section('bootstrap')
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-select@1.13.14/dist/css/bootstrap-select.min.css">
@endsection

@section('content')

<div class="form">
    <h2>{{ auth()->user()->name}}, we're glad you chose us.</h2>
    <form method="post" action="/library/create">
        @csrf
        <div class="row gtr-uniform">
            <h2>Book</h2>
            <!-- Break -->
            <div class="col-12">
                <input type="text" name="title" id="title" value="" placeholder="Your book's name" required=""/>
            </div>
            <div class="col-12">
                <select class="selectpicker" name="genres[]" multiple data-width="75%" title="Choose genre">
                    @foreach ($genres as $genre)
                        <option value="{{ $genre->id }}">{{ $genre->name }}</option>
                    @endforeach
                </select>
                @error('genres')
                    <p>{{ $message }}</p>
                @enderror
            </div>
            <!-- Break -->
            <div class="col-12">
                <textarea name="description" id="description" placeholder="Enter the book's description" rows="6"></textarea>
            </div>
            <!-- Break -->
            <div class="col-12">
                <ul class="actions">
                    <li><input type="submit" value="Send Message" class="primary" /></li>
                    <li><input type="reset" value="Reset" /></li>
                </ul>
            </div>
        </div>
    </form>
</div>
@endsection

@section('js-bootstrap')
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/bootstrap-select@1.13.14/dist/js/bootstrap-select.min.js"></script>
@endsection