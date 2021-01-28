@extends('layout')

@section('content')
<h1>List of all museums</h1>
<ul>
    @foreach ($museums as $museum)
        <li>
            <a href="/museums/{{ $museum->id }}"> 
                {{ $museum->name }}
            </a>
        </li>
    @endforeach
</ul>
@endsection
