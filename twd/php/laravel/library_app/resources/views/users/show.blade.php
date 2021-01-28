@extends('layout')

@section('content')
    <!-- Content -->
    <section>
        <header class="main">
            <h1>{{$user->name}}</h1>
        </header>

        <span class="image main"><img src="/images/pic11.jpg" alt="" /></span>
        <hr>

        <table class="alt">
            <thead>
                <tr>
                    <th>Book Name</th>
                    <th>Description</th>
                    <th>Genre</th>
                </tr>
            </thead>
            <tbody>
        @foreach ($user->books as $book)
            <tr>
                <td><a href="/library/{{ $book->id }}">{{ $book->title }}</a></td>
                <td>{{ $book->description }}</td>
                <td>@foreach ($book->genres as $genre)
                    {{ $genre->name }} 
                @endforeach
                </td>
            </tr>
        @endforeach
            </tbody>
        </table>
    </section>

</div>
</div>
@endsection