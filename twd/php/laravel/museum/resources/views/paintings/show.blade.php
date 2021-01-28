@extends('layout')

@section('content')
    <h1>{{ $painting->title }}</h1>
    <p>{{ $painting->description }}</p>
    <p>Created by <a href="/authors/{{ $painting->author->id }}">{{ $painting->author->name }}</a>, in {{ $painting->year_of_production }}</p>
    <hr>
    <br>

@endsection