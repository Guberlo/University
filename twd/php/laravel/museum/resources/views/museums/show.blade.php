@extends('layout')

@section('content')
    <h1>{{ $museum->name }}</h1>
    <p>Located in {{ $museum->city }}</p>
    <hr>
    <h2>Paintings</h2>
    <br>

    <ul>
        @foreach ($museum->paintings as $painting)
            <li style="margin-bottom: 1em">
                <a href="/paintings/{{ $painting->id }}">{{ $painting->title }}</a> by <a href="/authors/{{ $painting->author->id }}">{{ $painting->author->name }}</a>
                <br>
                {{ $painting->year_of_production }}
            </li>
        @endforeach
    </ul>
@endsection