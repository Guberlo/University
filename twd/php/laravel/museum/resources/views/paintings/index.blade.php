@extends('layout')

@section('content')
<h1>List of all paintings</h1>
<ul>
    @foreach ($paintings as $painting)
        <li>
            <a href="/paintings/{{ $painting->id }}"> 
                {{ $painting->title }}
            </a>
        </li>
    @endforeach
</ul>
@endsection